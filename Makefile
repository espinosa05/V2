# == SYMBOLS ==
CC=gcc
AR=ar
CFLAGS=-Wall -std=gnu11
SRC=src/
OUT=out/

V2SRC=\
      $(SRC)main.c

# custom self-maintained libraries:
# libcvk 	-> "c-vulkan" vulkan wrappers
# libcast 	-> "c-audio-stream" cross-platform audio io library
# libcwmr 	-> "c-window-management" cross-platform window managment api
# libcnet 	-> "c-networking" cross-platform networking api

LIBS=\
     $(OUT)libcvk.a \
     $(OUT)libcast.a \
     $(OUT)libcwmr.a \
     $(OUT)libcnet.a

# libcvk sources
# and directories
LIBCVK_DIR=src/libcvk/
LIBCVK_SRC=\
	   $(LIBCVK_DIR)cvk.c

# libcast sources
# and directories
LIBCAST_DIR=src/libcast/
LIBCAST_SRC=\
	   $(LIBCAST_DIR)cast.c

# libcwmr sources
# and directories
LIBCWMR_DIR=src/libcwmr/
LIBCWMR_SRC=\
	   $(LIBCWMR_DIR)cwmr.c

# libcnet sources
# and directories
LIBCNET_DIR=src/libcnet/
LIBCNET_SRC=\
	   $(LIBCNET_DIR)cnet.c

# == BUILD TARGETS ==
all: v2

clean: $(OUT)
	rm -rf $^

$(OUT):
	mkdir $@

v2: $(V2SRC) $(LIBS)
	$(CC) $(SRC) -I$(LIBCVK_DIR) $(CFLAGS)

# =============================================================================
# create libcvk static archive
# TODO: See if this makes any sense
# 	or if a dynamic library is
# 	easier to use
$(OUT)libcvk.a: $(OUT)libcvk.o
	$(AR) $^ -o $@

$(OUT)libcvk.o: $(LIBCVK_SRC)
	$(CC) $(CFLAGS) $^ -o $@
# =============================================================================

# =============================================================================
# create libcast static archive
$(OUT)libcast.a: $(OUT)libcast.o
	$(AR) $^ -o $@

$(OUT)libcast.o: $(LIBCAST_SRC)
	$(CC) $(CFLAGS) $^ -o $@
# =============================================================================

# =============================================================================
# create libcwmr static archive
$(OUT)libcwmr.a: $(OUT)libcwmr.o
	$(AR) $^ -o $@

$(OUT)libcwmr.o: $(LIBCWMR_SRC)
	$(CC) $(CFLAGS) $^ -o $@
# =============================================================================

# =============================================================================
# create libcnet static archive
$(OUT)libcnet.a: $(OUT)libcnet.o
	$(AR) $^ -o $@

$(OUT)libcnet.a: $(LIBCNET_SRC)
	$(CC) $(CFLAGS) $^ -o $@
# =============================================================================

