#
#
#
build_path = _build

#
.PHONY: __dummy__ build cleanup

__dummy__:
	@echo "make {build|cleanup}"

build:
	mkdir -p $(build_path)
	gcc -c Lock.c Operate.c Initializer.c
	mv *.o $(build_path)
	ar rcs $(build_path)/Buffer.a $(build_path)/*.o

cleanup:
	rm -rf $(build_path)
