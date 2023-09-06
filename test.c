#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>
#include <sys/epoll.h>

int main()
{
	//监听文件描述符
	int lfd = socket(AF_INET, SOCK_STREAM, 0);
	
	//端口复用
	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	//协议族，IP，端口
	struct sockaddr_in serv;
	serv.sin_family = AF_INET;
	serv.sin_port = htons(8888);
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	bind(lfd, (struct sockaddr *)&serv, sizeof(serv));

	//监听
	listen(lfd, 128);

	//epoll数根
	int epfd = epoll_create(1024);

	//事件节点
	struct epoll_event ev;
	ev.data.fd = lfd;
	ev.events = EPOLLIN;

	//事件节点上epoll树
	epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);

	int i;				//循环
	int n;				//read返回值
	int nready;			//内核监控结果
	int cfd;			//通信文件描述符
	int sockfd;			//事件节点文件描述符
	char buf[64];			//缓冲区
	struct epoll_event events[1024];//事件节点数组
	struct sockaddr_in client;
	char sIP[16];
	socklen_t len;
	while(1)
	{
		nready = epoll_wait(epfd, events, 1024, -1);
		//被信号中断
		if(nready < 0)
		{
			if(errno == EINTR)
			{
				continue;
			}
			break;
		}
		//遍历所有事件
		for(i=0; i<nready; i++)
		{
			sockfd = events[i].data.fd;
			if(sockfd == lfd)
			{
				//接收新的客户端连接
				len = sizeof(client);
				cfd = accept(lfd, (struct sockaddr*)&client, &len);
			
				//打印新连接的ip 端口
				printf("new client:ip[%s],port[%d]\n", 
					inet_ntop(AF_INET, &client.sin_addr.s_addr, 
					sIP, sizeof(sIP)), ntohs(client.sin_port));

				ev.events = EPOLLIN;
				ev.data.fd = cfd;
				//将新的连接文件描述符上树
				epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
				continue;
			}
			//读数据
			memset(buf, 0x00, sizeof(buf));
			n = read(sockfd, buf, sizeof(buf));
			//若没读到
			if(n <= 0)
			{
				//关闭文件描述符
				close(sockfd);
				//下树
				epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
				printf("client[%s][%d]close\n", sIP, client.sin_port);
				continue;
			}

			printf("from[%s]:%s\n", sIP, buf);
			//写数据
			write(sockfd, buf, n);
		}
	}





	close(lfd);
	close(cfd);



	return 0;
}
