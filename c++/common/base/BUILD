cc_library(
    name = "class_register",
    hdrs = ["class_register.h"],
)

cc_library(
    name = "class_register_test_header",
    hdrs = ["class_register_test.h"],
)

cc_test(
    name = "class_register_test",
    srcs = ["class_register_test.cc"],
    deps = [
        ":class_register",
        ":class_register_test_header",
        "@com_google_googletest//:gtest",
    ],
)
