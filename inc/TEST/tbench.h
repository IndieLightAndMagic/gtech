#ifndef __TBENCH_H__
#define __TBENCH_H__

#define UINT_TEST_OK 1
#define UINT_TEST_FAIL 0 
#define BOOL_TEST_OK true
#define BOOL_TEST_FAIL false 


#define TEST_INT(prb,xpr) prb = prb &(xpr==1?true:false); \
	std::cout << __FILE__ << " @ " << __LINE__ << " : [TST] " << (prb ? "OK":"FAILED") <<std::endl

#define	TEST_RESULT(tr) std::cout << (tr?"TEST_PASSED":"TEST_NOT_PASSED") << std::endl; \
		return (tr==true?0:1);


#endif /* __TBENCH_H__ */


