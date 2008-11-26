--TEST--
Test fopen() function : variation: use include path create a file (relative)
--CREDITS--
Dave Kelsey <d_kelsey@uk.ibm.com>
--XFAIL--
--FILE--
<?php
/* Prototype  : resource fopen(string filename, string mode [, bool use_include_path [, resource context]])
 * Description: Open a file or a URL and return a file pointer 
 * Source code: ext/standard/file.c
 * Alias to functions: 
 */

require_once('fopen_include_path.inc');

echo "*** Testing fopen() : variation ***\n";
$thisTestDir = "fopenVariation7.dir";
mkdir($thisTestDir);
chdir($thisTestDir);

$newpath = create_include_path();
set_include_path($newpath);
runtest();
$newpath = generate_next_path();
set_include_path($newpath);
runtest();

teardown_include_path();
restore_include_path();
chdir("..");
rmdir($thisTestDir);

function runtest() {
    global $dir1;
	$tmpfile = 'fopen_variation7.tmp';
	$h = fopen($tmpfile, "w", true);
	fwrite($h, "This is the test file");
	fclose($h);
	
	
	$h = @fopen($tmpfile, "r");
	if ($h === false) {
	   echo "Not created in working dir\n";
	}
	else {
	   echo "created in working dir\n";
	   fclose($h);
	   unlink($tmpfile);
	}
	
	$h = fopen($dir1.'/'.$tmpfile, "r");
	if ($h === false) {
	   echo "Not created in dir1\n";
	}
	else {
	   echo "created in dir1\n";
	   fclose($h);
	   unlink($dir1.'/'.$tmpfile);   
	}
}
?>
===DONE===
--EXPECT--
*** Testing fopen() : variation ***
Not created in working dir
created in dir1
Not created in working dir
created in dir1
===DONE===
