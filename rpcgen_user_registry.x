struct rpc_in_login_details {
	char username[256];
	char password[256];
};
struct rpc_out_svr_response {
	long response_code;
	char response_msg[256];
	long num_users;
};

program REGISTER_USER_PROG {
	version REGISTER_USER_VERS {
		rpc_out_svr_response REGISTER_USER_PROC(rpc_in_login_details) = 1;
		rpc_out_svr_response USER_LOGIN_PROC(rpc_in_login_details) = 2;
		} = 1;
} = 0x13451111;
