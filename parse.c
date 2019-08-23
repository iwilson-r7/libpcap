#include <emscripten.h>

#include <pcap.h>

void
pcap_fmt_errmsg_for_errno(char *errbuf, size_t errbuflen, int errnum, const char *fmt, ...) {
  // No-op, can't link to stdlib for errno with emscripten
}

int EMSCRIPTEN_KEEPALIVE parse(char *buf) {
  int snaplen = 65536;
  int linktype = DLT_EN10MB;

  struct bpf_program program = { 0 };

  return pcap_compile_nopcap(
    snaplen,
    linktype,
    &program,
    buf,
    0, // No optimization
    0  // Netmask (everything)
  );
}
