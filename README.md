```
lex -P pcap_ --header-file=scanner.h --nounput -o scanner.c < scanner.l
yacc -p pcap_ -o grammar.c -d grammar.y

emcc \
  optimize.c \
  pcap.c \
  etherent.c \
  nametoaddr.c \
  missing/strlcpy.c \
  gencode.c \
  scanner.c \
  grammar.c \
  parse.c \
  "-DPACKAGE_VERSION=\"none\"" \
  -I. \
  -O3 \
  -o hello.html \
  -s NO_EXIT_RUNTIME=1 \
  -s "EXTRA_EXPORTED_RUNTIME_METHODS=['ccall', 'cwrap']"
```