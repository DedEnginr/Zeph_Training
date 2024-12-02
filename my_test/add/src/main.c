/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/ztest.h>


static int add(int a, int b)
{
	return a+b;
}



ZTEST(adder, test_adder)
{
	zassert_equal(add(2,1),3,"2 and 1 gives 3 dumbass");

}


ZTEST_SUITE(adder,NULL,NULL,NULL,NULL,NULL);


