#include <emscripten.h>

#include <pcap.h>
#include <portability.h>

void
pcap_fmt_errmsg_for_errno(char *errbuf, size_t errbuflen, int errnum, const char *fmt, ...) {
  // No-op, can't link to stdlib for errno with emscripten
}

static char last_error[1000];

const char* EMSCRIPTEN_KEEPALIVE parse(char *buf) {
  int snaplen = 65536;
  int linktype = DLT_EN10MB;

  struct bpf_program program = { 0 };

  pcap_t *p;

  int result;
  const char *ret;

  p = pcap_open_dead(linktype, snaplen);

  if (p == NULL)
    return "Failed to initialize parser";

  result = pcap_compile(
    p,
    &program,
    buf,
    0, // No optimization
    0  // Netmask (everything)
  );

  if (result != 0) {
    pcap_strlcpy(last_error, pcap_geterr(p), sizeof(last_error));

    ret = last_error;

    if (*last_error == 0) {
      ret = "Unknown error";
    }
  }

  pcap_close(p);

  return ret;
}
