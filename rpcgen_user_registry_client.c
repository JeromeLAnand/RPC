#include "rpcgen_user_registry.h"


void
user_login_prog_1(char *host)
{
	CLIENT *clnt;
	rpc_out_svr_response  *result;
	char uname[255];
	char input;
	char password[255];
	rpc_in_login_details reg_info;

#ifndef	DEBUG
	clnt = clnt_create (host, REGISTER_USER_PROG, REGISTER_USER_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	printf("\n\t\tLogin");
	printf("\n\t\t*****");
	printf("\n\t\t User Name : ");
	scanf("%s", uname);
	strcpy(reg_info.username, uname);
	printf("\n\t\t Password : ");
	scanf("%s",password);
	strcpy(reg_info.password, password);

	result = user_login_proc_1(&reg_info, clnt);
	if (result == (rpc_out_svr_response *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	if (result->response_code != 0) {
		printf("\n\n\t\tWelcome <%s> ! \n",uname);
		if (!strcmp(uname, "admin")) {
			printf("\n\n\t\tTotal number of Registered users are : <%ld> \n",(result->num_users));
		}
	} else {
		printf("\n\t ERROR !! Invalid user. Try again \n");
	}
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}

void
register_user_prog_1(char *host)
{
	CLIENT *clnt;
	rpc_out_svr_response  *result;
	char uname[255];
	char input;
	char password[255];
	rpc_in_login_details reg_info;

#ifndef	DEBUG
	clnt = clnt_create (host, REGISTER_USER_PROG, REGISTER_USER_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

	printf("\n\n\t\tNew User Registration");
	printf("\n\t\t*********************");
	printf("\n\t\t User Name : ");
	scanf("%s", uname);
	strcpy(reg_info.username, uname);
	printf("\n\t\t Password : ");
	scanf("%s",password);
	strcpy(reg_info.password, password);

	if (!strcmp(uname, "admin")) {
		printf("\n\t ERROR !! You cannot user SUPER USER NAME FOR REGISTRATION \n");
		exit(0);
	}

	result = register_user_proc_1(&reg_info, clnt);
	if (result == (rpc_out_svr_response *) NULL) {
		clnt_perror (clnt, "call failed");
	}
	if(result->response_code != 0) {
		printf("\n\t\t Registration Successful");
		printf("\n\n\t Do you wish to login ? (y/n) : ");
		getchar();
		scanf("%c",&input);
		if ((input == 'y'))
			user_login_prog_1(host);
		else {
			printf("\n\t Exiting application !!\n");
			exit(0);
		}

	} else {
		printf("\n\t ERROR!! Username already exists, Try a different one\n");
	}

#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


static print_author_details() {
	printf("\n---------------------------------------------- \n");
	printf("\t Distributed Computing Assignment 1 \n");
	printf("Name \t : Jerome Anand \n");
	printf("ID   \t : 2015HT12068 \n");
	printf("---------------------------------------------- \n");
}

int
main (int argc, char *argv[])
{
	char *host;
	int user_input;

	if (argc < 2) {
		printf ("usage: %s server_host (localhost)\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	
	print_author_details();

	do {
		printf("\n\t USER REGISTRY APPLICATION");
		printf("\n\t *************************");
		printf("\n\t 1. User Registration");
		printf("\n\t 2. User Login");
		printf("\n\t 3. Exit");

		printf("\n\n\t Please enter a choice of preference :: ");
		scanf("%d",&user_input);

		switch(user_input) {
			case 1:
				printf("\n\t Registering User ...\n");
				register_user_prog_1 (host);
				break;
			case 2:
				printf("\n\t Logging User ...\n");
				user_login_prog_1 (host);
				break;
			default:
				printf("\n\t Option not yet supported !! \n");
			case 3:
				printf("\n\t Exiting applicaton !! \n");
				break;
		}
		if (user_input == 3) {
			printf("\n\t App Close %d \n", user_input);
			break;
		}
	} while(1);

exit (0);
}
