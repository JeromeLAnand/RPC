#include "rpcgen_user_registry.h"

typedef enum {
	UNKNOWN_ERROR = 0,
	USER_AVAILABLE = 1,
	SUPER_USER,
	USER_ADD,
	USER_DELETE,
}UserState;

#define USER_REG_DB "./user_registry.db"

static long get_user_count() {
   	
	long user_count = 0;
	int ch = 0;

	FILE *db = fopen(USER_REG_DB,"r");

      	if(db != NULL) {
		while ((ch = fgetc(db)) != EOF) {
			if (ch == '\n')
				++user_count;
		}
	}
	return user_count;
}

void updateDB(rpc_in_login_details *argp,int type) {

   	FILE *db = fopen(USER_REG_DB,"ab");

      	if(db != NULL) {
		char softDB[512]  = "";

		strcpy(softDB,argp->username);
		strcat(softDB,"---");
		strcat(softDB,argp->password);
		strcat(softDB,"\n");
		fputs(softDB,db);
		fclose(db);
	}
	return; 
}

int is_user_available(rpc_in_login_details *argp) {

	int availability = 0;
    	FILE *db;
    	char *line = NULL;
    	size_t len = 0;
    	ssize_t read;

    	char softDB[512];
	
	if ((strncmp(argp->username,"admin",5) ==0 ) && 
			(strcmp(argp->password,"bits") == 0)) {
		printf("\n Server Access ::\n\t user: Admin \n");
		availability = 1;
		return availability;
	}

    	strcpy(softDB,argp->username);
    	strcat(softDB,"---");
    	strcat(softDB,argp->password);
    	strcat(softDB,"\n");

	printf("\n Server Access ::\n\t user: %s pwd : %s \n",argp->username, argp->password);
    	db = fopen(USER_REG_DB,"r");
    	if(db == NULL){
		printf("\n\t user Database unavaialble.. creating new DB.. \n");
		return availability;
	}

    	while((read = getline(&line, &len, db)) != -1) {
		if(strcmp(line,softDB)==0) {
		    	    availability = 1;
		    	    break;
		}
        }

	fclose(db);

	return availability;
}

rpc_out_svr_response *
register_user_proc_1_svc(rpc_in_login_details *argp, struct svc_req *rqstp)
{
	static rpc_out_svr_response  result;

	/*
	 * insert server code here
	 */
	if (!is_user_available(argp)) {
		updateDB(argp, USER_ADD);
		result.response_code = USER_ADD;
		printf("\n Server Access :: \n\t New user added \n");
	} else {
		result.response_code = UNKNOWN_ERROR;
	}

	return &result;
}

rpc_out_svr_response *
user_login_proc_1_svc(rpc_in_login_details *argp, struct svc_req *rqstp)
{
	static rpc_out_svr_response  result;

	/*
	 * insert server code here
	 */
	if (is_user_available(argp)) {
		result.response_code = USER_AVAILABLE;
		result.num_users = get_user_count();
	} else {
		result.response_code = UNKNOWN_ERROR;
	}

	return &result;
}
