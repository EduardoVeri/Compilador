#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

// Example function to be tested
int add(int a, int b) {
    return a + b;
}

// Unit test for the add function
static void test_add(void **state) {
    (void) state; // unused variable
    assert_int_equal(add(2, 3), 5);
    assert_int_equal(add(-1, 1), 0);
    assert_int_equal(add(-1, -1), -2);
}

int main(void) {
    const struct CMUnitTest tests[] = {
        cmocka_unit_test(test_add),
    };

    return cmocka_run_group_tests(tests, NULL, NULL);
}
