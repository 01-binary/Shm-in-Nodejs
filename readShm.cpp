#include <iostream>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string>
#include <node_api.h>
#include <assert.h>

const int KEY_SIZE =32;

using namespace std;


napi_value Method(napi_env env, napi_callback_info info) {

	int shmid;
	key_t key;

	key=0x0002cab7;
	char* data;

	napi_status status;
	napi_value string;

    if((shmid=shmget(key, KEY_SIZE, IPC_CREAT|0666)) == -1) {
      cout << "shmget failed" << endl;
    }

    if((data=(char *)shmat(shmid, (void *)0, 0)) == (void *)-1) {
       cout << "shmat failed." << endl;
    }

    status = napi_create_string_utf8(env, data, NAPI_AUTO_LENGTH, &string);
	assert(status== napi_ok);

	return string;


}


#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("readShm", Method);
  status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init)

