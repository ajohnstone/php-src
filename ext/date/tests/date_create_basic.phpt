--TEST--
Test date_create() function : basic functionality 
--FILE--
<?php
/* Prototype  : DateTime date_create  ([ string $time  [, DateTimeZone $timezone  ]] )
 * Description: Returns new DateTime object
 * Source code: ext/date/php_date.c
 * Alias to functions: DateTime::__construct
 */

//Set the default time zone 
date_default_timezone_set("Europe/London");

echo "*** Testing date_create() : basic functionality ***\n";

var_dump( date_create() );

var_dump( date_create("GMT") );
var_dump( date_create("2005-07-14 22:30:41") );
var_dump( date_create("2005-07-14 22:30:41 GMT") );

?>
===DONE===
--EXPECTF--
*** Testing date_create() : basic functionality ***
object(DateTime)#%d (3) {
  [u"date"]=>
  unicode(19) "%s"
  [u"timezone_type"]=>
  int(3)
  [u"timezone"]=>
  unicode(13) "Europe/London"
}
object(DateTime)#%d (3) {
  [u"date"]=>
  unicode(19) "%s"
  [u"timezone_type"]=>
  int(2)
  [u"timezone"]=>
  unicode(3) "GMT"
}
object(DateTime)#%d (3) {
  [u"date"]=>
  unicode(19) "2005-07-14 22:30:41"
  [u"timezone_type"]=>
  int(3)
  [u"timezone"]=>
  unicode(13) "Europe/London"
}
object(DateTime)#%d (3) {
  [u"date"]=>
  unicode(19) "2005-07-14 22:30:41"
  [u"timezone_type"]=>
  int(2)
  [u"timezone"]=>
  unicode(3) "GMT"
}
===DONE===