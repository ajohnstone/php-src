--TEST--
Bug #41287 (Namespace functions don't allow xmlns defintion to be optional)
--FILE--
<?php

$xw = xmlwriter_open_memory();
xmlwriter_set_indent($xw, true);
xmlwriter_start_document($xw);
xmlwriter_start_element_ns($xw, 'test', 'test', 'urn:x-test:');
xmlwriter_write_element_ns($xw, 'test', 'foo', null, '');
xmlwriter_write_element_ns($xw, null, 'bar', 'urn:x-test:', '');
xmlwriter_write_element_ns($xw, null, 'bar', '', '');
xmlwriter_end_element($xw);
xmlwriter_end_document($xw);
print xmlwriter_flush($xw, true);
print "\n";

$xw = new XMLWriter();
$xw->openMemory();
$xw->setIndent(true);
$xw->startDocument();
$xw->startElementNS('test', 'test', 'urn:x-test:');
$xw->writeElementNS('test', 'foo', null, '');
$xw->writeElementNS(null, 'bar', 'urn:x-test:', '');
$xw->writeElementNS(null, 'bar', '', '');
$xw->endElement();
$xw->endDocument();
print $xw->flush(true);
?>
--EXPECTF--
<?xml version="1.0"?>
<test:test xmlns:test="urn:x-test:">
 <test:foo/>
 <bar xmlns="urn:x-test:"/>
 <bar xmlns=""/>
</test:test>

<?xml version="1.0"?>
<test:test xmlns:test="urn:x-test:">
 <test:foo/>
 <bar xmlns="urn:x-test:"/>
 <bar xmlns=""/>
</test:test>
