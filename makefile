#
#
#
build_path = _build

#
.PHONY: __dummy__ build cleanup

__dummy__:
	@echo "make {build|cleanup}"

build:
	@mkdir -p $(build_path)

	@echo "compiling..."
	@gcc -c Lock.c Operate.c Initializer.c
	@mv *.o $(build_path)

	@echo "archiving..."
	@cd $(build_path); gcc *.o -fPIC -shared -o Buffer.so

cleanup:
	@cd $(build_path);rm -f *
