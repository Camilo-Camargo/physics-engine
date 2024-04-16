#include <libwebsockets.h>
#include <signal.h>
#include <string.h>

static int callback_physics_engine(struct lws *wsi,
                                   enum lws_callback_reasons reason, void *user,
                                   void *in, size_t len) {

  switch (reason) {

  case LWS_CALLBACK_RECEIVE: {
    char *input = (char *)in;
    lwsl_user("Hello World");
    lwsl_user("%s", input);
    lws_callback_on_writable_all_protocol(lws_get_context(wsi),
                                          lws_get_protocol(wsi));
    break;
  }

  case LWS_CALLBACK_SERVER_WRITEABLE: {
    const char *hello = "Hello World";
    size_t len = strlen(hello);
    unsigned char *buf = malloc(LWS_PRE + len);
    if (buf) {
      memcpy(buf + LWS_PRE, hello, len);
      lws_write(wsi, buf + LWS_PRE, len, LWS_WRITE_TEXT);
      free(buf);
    }
  }
  case LWS_CALLBACK_ESTABLISHED:
    lwsl_user("Connection established\n");
    lws_set_timer_usecs(wsi, 20 * LWS_USEC_PER_SEC);
    lws_set_timeout(wsi, 1, 60);
    break;

  case LWS_CALLBACK_CLOSED:
    lwsl_user("Connection closed\n");
    break;

  default:
    break;
  }
  return 0;
}

static struct lws_protocols protocols[] = {
    {"http", lws_callback_http_dummy, 0, 0, 0, NULL, 0},
    {"physics-engine", callback_physics_engine, 0, 0, 0, NULL, 0},
    LWS_PROTOCOL_LIST_TERM};

static int interrupted;
void sigint_handler(int sig) { interrupted = 1; }

int main(int argc, const char **argv) {
  struct lws_context_creation_info info;
  struct lws_context *context;

  signal(SIGINT, sigint_handler);

  // log level
  const char *p;
  int n = 0, logs = LLL_USER | LLL_ERR | LLL_WARN | LLL_NOTICE;

  if ((p = lws_cmdline_option(argc, argv, "-d")))
    logs = atoi(p);

  lws_set_log_level(logs, NULL);
  lwsl_user("LWS minimal ws server | visit http://localhost:7681 (-s = use TLS "
            "/ https)\n");

  memset(&info, 0, sizeof info);
  info.port = 7681;
  info.protocols = protocols;
  info.vhost_name = "localhost";
  info.options = LWS_SERVER_OPTION_HTTP_HEADERS_SECURITY_BEST_PRACTICES_ENFORCE;

  context = lws_create_context(&info);

  if (!context) {
    lwsl_err("lws init failed\n");
    return 1;
  }

  while (n >= 0 && !interrupted) {
    n = lws_service(context, 0);
  }

  lws_context_destroy(context);

  return 0;
}
