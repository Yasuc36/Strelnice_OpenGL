Doxygen-README.txt
==================

Comment your code using the doxygen documenting system style (https://www.doxygen.nl/download.html).
Start documenting using provided Doxyfile by the commands: 
	cd doxygen
	doxygen
Modify the Doxyfile, if you like.

The generated documentation intro page is in doxygen/html/index.html
 
Current doxygen setup (changes in the generated Doxyfile):
----------------------------------------------------------
EXTRACT_ALL            = YES
INPUT                  = ..
FILTER_SOURCE_FILES    = YES
SOURCE_BROWSER         = YES
INLINE_SOURCES         = YES
GENERATE_LATEX         = NO

 