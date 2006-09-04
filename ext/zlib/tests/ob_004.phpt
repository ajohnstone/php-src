--TEST--
ob_gzhandler
--SKIPIF--
<?php
if (!extension_loaded("zlib")) die("skip need ext/zlib");
if (false === stristr(PHP_SAPI, "cgi")) die("skip need sapi/cgi");
?>
--INI--
zlib.output_compression=0
--ENV--
HTTP_ACCEPT_ENCODING=gzip
--FILE--
<?php
ob_start("ob_gzhandler");
echo "hi\n";
?>
--EXPECTF--
%s
Content-Encoding: gzip
Vary: Accept-Encoding
%s

�%s
