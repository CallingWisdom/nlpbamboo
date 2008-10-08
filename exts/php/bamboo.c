#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "php_bamboo.h"

#include "ibamboo.hxx"

static function_entry bamboo_functions[] = {
    PHP_FE(bamboo_open, NULL)
    PHP_FE(bamboo_parse, NULL)
    PHP_FE(bamboo_close, NULL)
    {NULL, NULL, NULL}
};

zend_module_entry bamboo_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_BAMBOO_EXTNAME,
    bamboo_functions,
    PHP_MINIT(bamboo),
    PHP_MSHUTDOWN(bamboo),
    NULL,
    NULL,
    NULL,
#if ZEND_MODULE_API_NO >= 20010901
    PHP_BAMBOO_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_BAMBOO
ZEND_GET_MODULE(bamboo)
#endif


PHP_INI_BEGIN()
PHP_INI_ENTRY("bamboo.configuration", "xxx", PHP_INI_ALL, NULL)
PHP_INI_END()

void *handle;


PHP_MINIT_FUNCTION(bamboo)
{
	REGISTER_INI_ENTRIES();

	handle = (void *)bamboo_init(INI_STR("bamboo.configuration"));
	if (!handle) return FAILURE;

    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(bamboo)
{
	UNREGISTER_INI_ENTRIES();
	bamboo_clean(handle);
    return SUCCESS;
}

PHP_FUNCTION(bamboo_open)
{
    RETURN_STRING("not impl", 1);
}

PHP_FUNCTION(bamboo_parse)
{
	char *t = NULL, *s = NULL;
	int size;
		
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &s, &size) == FAILURE)
		RETURN_NULL();

	t = (char *)emalloc((size << 1) + 1);
	bamboo_parse(handle, t, s);
	if (!t) RETURN_NULL();
	RETURN_STRING(t, 1);
}

PHP_FUNCTION(bamboo_close)
{
    RETURN_STRING("not impl", 1);
}
