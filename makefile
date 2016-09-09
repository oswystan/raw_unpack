all: raw_unpack

raw_unpack:raw_unpack.c
	gcc $^ -o $@

clean:
	rm -f raw_unpack
