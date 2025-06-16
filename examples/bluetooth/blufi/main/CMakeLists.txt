idf_component_register(SRCS "blufi_example_main.c"
                            "blufi_security.c"
                            "blufi_init.c"
                            "blufi_server.cpp"
                            "blufi_example_main_cpp.cpp"
                    PRIV_REQUIRES bt nvs_flash mbedtls
                    INCLUDE_DIRS ".")
