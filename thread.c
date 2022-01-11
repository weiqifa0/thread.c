pthread_mutex_t lock_common;

void *thread_a_hdl(void *data){
	static int i = 0;
	while(1){
		cvi_printf("%s, locking.cn=%d\n", __func__,++i);
		pthread_mutex_lock(&lock_common);
		cvi_printf("%s, locked.\n", __func__);
		usleep(500*1000);
	}
}

void *thread_b_hdl(void *data){
	static int i = 0;
	while(1){
		usleep(500*1000);
		cvi_printf("%s, locking.cn=%d\n", __func__,++i);
		pthread_mutex_unlock(&lock_common);
		cvi_printf("%s, unlocked.\n", __func__);
		usleep(500*1000);
	}
}

void test_pthread(void){
	cvi_printf("%s enter.\n", __func__);

	struct sched_param param;
	pthread_attr_t attr;
	param.sched_priority = 85;
	pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);

	pthread_t thread_a;
	pthread_t thread_b;
	pthread_mutex_init(&lock_common, NULL);
	pthread_create(&thread_a, NULL, (void *)thread_a_hdl, NULL);
	usleep(1000);
	pthread_create(&thread_b, NULL, (void *)thread_b_hdl, NULL);
	for (;;) {
		sleep(1);
		cvi_printf("CVI_VPSS_SendFrame .....freeHeapSize.\n");
	}
}
