/*
   +----------------------------------------------------------------------+
   | PHP Version 4                                                        |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997-2003 The PHP Group                                |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.0 of the PHP license,       |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_0.txt.                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Authors: Christian Stocker <chregu@php.net>                          |
   |          Rob Richards <rrichards@php.net>                            |
   +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#if HAVE_LIBXML && HAVE_DOM
#include "php_dom.h"


/*
* class domnamednodemap 
*
* URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-1780488922
* Since: 
*/

zend_function_entry php_dom_namednodemap_class_functions[] = {
	PHP_FALIAS(getNamedItem, dom_namednodemap_get_named_item, NULL)
	PHP_FALIAS(setNamedItem, dom_namednodemap_set_named_item, NULL)
	PHP_FALIAS(removeNamedItem, dom_namednodemap_remove_named_item, NULL)
	PHP_FALIAS(item, dom_namednodemap_item, NULL)
	PHP_FALIAS(getNamedItemNS, dom_namednodemap_get_named_item_ns, NULL)
	PHP_FALIAS(setNamedItemNS, dom_namednodemap_set_named_item_ns, NULL)
	PHP_FALIAS(removeNamedItemNS, dom_namednodemap_remove_named_item_ns, NULL)
	{NULL, NULL, NULL}
};

/* {{{ attribute protos, not implemented yet */

/* {{{ proto length	unsigned long	
readonly=yes 
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-6D0FB19E
Since: 
*/
int dom_namednodemap_length_read(dom_object *obj, zval **retval TSRMLS_DC)
{
	dom_nnodemap_object *objmap;
	xmlAttrPtr curnode;
	xmlNodePtr nodep;
	int count = 0;

	objmap = (dom_nnodemap_object *)obj->ptr;
	if (objmap->ht) {
		count = xmlHashSize(objmap->ht);
	} else {
		nodep = dom_object_get_node(objmap->baseobj);
		if (nodep) {
			curnode = nodep->properties;
			if (curnode) {
				count++;
				while (curnode->next != NULL) {
					count++;
					curnode = curnode->next;
				}
			}
		}
	}

	MAKE_STD_ZVAL(*retval);
	ZVAL_LONG(*retval, count);
	return SUCCESS;
}

/* }}} */




/* {{{ proto domnode dom_namednodemap_get_named_item(string name);
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-1074577549
Since: 
*/
PHP_FUNCTION(dom_namednodemap_get_named_item)
{
	zval *id, *rv = NULL;
	int ret, namedlen=0;
	dom_object *intern;
	xmlNodePtr itemnode = NULL;
	char *named;

	dom_nnodemap_object *objmap;
	xmlNodePtr nodep;
	xmlNotation *notep = NULL;

	id = getThis();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &named, &namedlen) == FAILURE) {
		return;
	}

	intern = (dom_object *)zend_object_store_get_object(id TSRMLS_CC);

	objmap = (dom_nnodemap_object *)intern->ptr;
	if (objmap->ht) {
		if (objmap->nodetype == XML_ENTITY_NODE) {
			itemnode = (xmlNodePtr)xmlHashLookup(objmap->ht, named);
		} else {
			notep = (xmlNotation *)xmlHashLookup(objmap->ht, named);
			itemnode = create_notation(notep->name, notep->PublicID, notep->SystemID);
		}
	} else {
		nodep = dom_object_get_node(objmap->baseobj);
		if (nodep) {
			itemnode = (xmlNodePtr)xmlHasProp(nodep, named);
		}
	}

	if (itemnode) {
		DOM_RET_OBJ(rv, itemnode, &ret, objmap->baseobj);
	} else {
		RETVAL_NULL();
	}
}
/* }}} end dom_namednodemap_get_named_item */


/* {{{ proto domnode dom_namednodemap_set_named_item(node arg);
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-1025163788
Since: 
*/
PHP_FUNCTION(dom_namednodemap_set_named_item)
{
 DOM_NOT_IMPLEMENTED();
}
/* }}} end dom_namednodemap_set_named_item */


/* {{{ proto domnode dom_namednodemap_remove_named_item(string name);
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-D58B193
Since: 
*/
PHP_FUNCTION(dom_namednodemap_remove_named_item)
{
 DOM_NOT_IMPLEMENTED();
}
/* }}} end dom_namednodemap_remove_named_item */


/* {{{ proto domnode dom_namednodemap_item(unsigned long index);
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-349467F9
Since: 
*/
PHP_FUNCTION(dom_namednodemap_item)
{
	zval *id, *rv = NULL;
	int index, ret;
	dom_object *intern;
	xmlNodePtr itemnode = NULL;

	dom_nnodemap_object *objmap;
	xmlNodePtr nodep, curnode;
	int count;

	id = getThis();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "l", &index) == FAILURE) {
		return;
	}

	if (index >= 0) {
		intern = (dom_object *)zend_object_store_get_object(id TSRMLS_CC);

		objmap = (dom_nnodemap_object *)intern->ptr;
		if (objmap->ht) {
			if (objmap->nodetype == XML_ENTITY_NODE) {
				itemnode = php_dom_libxml_hash_iter(objmap->ht, index);
			} else {
				itemnode = php_dom_libxml_notation_iter(objmap->ht, index);
			}
		} else {
			nodep = dom_object_get_node(objmap->baseobj);
			if (nodep) {
				curnode = (xmlNodePtr)nodep->properties;
				count = 0;
				while (count < index && curnode != NULL) {
					count++;
					curnode = (xmlNodePtr)curnode->next;
				}
				itemnode = curnode;
			}
		}
	} else {
		RETURN_NULL();
	}

	if (itemnode) {
		DOM_RET_OBJ(rv, itemnode, &ret, objmap->baseobj);
	} else {
		RETVAL_NULL();
	}
}
/* }}} end dom_namednodemap_item */


/* {{{ proto domnode dom_namednodemap_get_named_item_ns(string namespaceURI, string localName);
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-getNamedItemNS
Since: DOM Level 2
*/
PHP_FUNCTION(dom_namednodemap_get_named_item_ns)
{
	zval *id, *rv = NULL;
	int ret, namedlen=0, urilen=0;
	dom_object *intern;
	xmlNodePtr itemnode = NULL;
	char *uri, *named;

	dom_nnodemap_object *objmap;
	xmlNodePtr nodep;
	xmlNotation *notep = NULL;

	id = getThis();
	
	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &uri, &urilen, &named, &namedlen) == FAILURE) {
		return;
	}

	intern = (dom_object *)zend_object_store_get_object(id TSRMLS_CC);

	objmap = (dom_nnodemap_object *)intern->ptr;
	if (objmap->ht) {
		if (objmap->nodetype == XML_ENTITY_NODE) {
			itemnode = (xmlNodePtr)xmlHashLookup(objmap->ht, named);
		} else {
			notep = (xmlNotation *)xmlHashLookup(objmap->ht, named);
			itemnode = create_notation(notep->name, notep->PublicID, notep->SystemID);
		}
	} else {
		nodep = dom_object_get_node(objmap->baseobj);
		if (nodep) {
			itemnode = (xmlNodePtr)xmlHasNsProp(nodep, named, uri);
		}
	}

	if (itemnode) {
		DOM_RET_OBJ(rv, itemnode, &ret, objmap->baseobj);
	} else {
		RETVAL_NULL();
	}
}
/* }}} end dom_namednodemap_get_named_item_ns */


/* {{{ proto domnode dom_namednodemap_set_named_item_ns(node arg);
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-setNamedItemNS
Since: DOM Level 2
*/
PHP_FUNCTION(dom_namednodemap_set_named_item_ns)
{
 DOM_NOT_IMPLEMENTED();
}
/* }}} end dom_namednodemap_set_named_item_ns */


/* {{{ proto domnode dom_namednodemap_remove_named_item_ns(string namespaceURI, string localName);
URL: http://www.w3.org/TR/2003/WD-DOM-Level-3-Core-20030226/DOM3-Core.html#core-ID-removeNamedItemNS
Since: DOM Level 2
*/
PHP_FUNCTION(dom_namednodemap_remove_named_item_ns)
{
 DOM_NOT_IMPLEMENTED();
}
/* }}} end dom_namednodemap_remove_named_item_ns */
#endif
