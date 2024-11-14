# generate the flags

.PHONY: all

all: buffovf buffovf_stackp buffovf_aslr

buffovf: buffovf.c
	gcc $< -o $@ -std=c99 -Wno-deprecated-declarations -fno-stack-protector \
		-no-pie -fno-pic -m32 -g

buffovf_stackp: buffovf.c
	gcc $< -o $@ -std=c99 -Wno-deprecated-declarations \
		-no-pie -fno-pic -m32 -g

buffovf_aslr: buffovf.c
	gcc $< -o $@ -std=c99 -Wno-deprecated-declarations -pie -fno-stack-protector -m32 -g

clean:
	rm -f buffovf buffovf_stackp buffovf_aslr
