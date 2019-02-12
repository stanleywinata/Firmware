px4_add_module(
	MODULE examples__coolapp
	MAIN coolapp
	COMPILE_FLAGS
	SRCS
		coolapp.c
	DEPENDS
    #platforms__common
)
