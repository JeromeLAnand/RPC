
client: rpcgen_user_registry_client.c rpcgen_user_registry_clnt.c rpcgen_user_registry_xdr.c
	gcc -o client rpcgen_user_registry_client.c rpcgen_user_registry_clnt.c rpcgen_user_registry_xdr.c -lnsl

server: rpcgen_user_registry_server.c rpcgen_user_registry_svc.c rpcgen_user_registry_xdr.c
	gcc -o server rpcgen_user_registry_server.c rpcgen_user_registry_svc.c rpcgen_user_registry_xdr.c -lrpcsvc -lnsl

all:
	make client 
	make server

clean:
	rm -rf client rpcgen_user_registry_client.o rpcgen_user_registry_clnt.o rpcgen_user_registry_xdr.o
	rm -rf server rpcgen_user_registry_server.o rpcgen_user_registry_svc.o rpcgen_user_registry_xdr.o
