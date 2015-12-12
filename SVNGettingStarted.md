# Getting started with SVN #

  1. Checking out code: (see http://code.google.com/p/jawpintos/source/checkout for details on password generation) with say 'jawpintos' as root directory (you can name this anything you want):
```
> svn checkout https://jawpintos.googlecode.com/svn/trunk/ jawpintos --username your_gmail_id
```
  1. We'll use the sandbox directory to play around. Adding a file (say mynewfile.txt) to  the sandbox directory:
```
> cd jawpintos
jawpintos> cd sandbox
jawpintos/sandbox> svn add mynewfile.txt
```
  1. Edit an existing file using vi or any other IDE:
```
jawpintos/sandbox> vi README.txt (make some changes)
```
  1. Seeing what files are changed in your local 'checked out' version that are not yet 'committed' into the repository (Status codes: M: your changes need to be merged to repository, C: conflicts exist and you need to resolve them, A: you added your file to the repository, you still need to add them, ?: File is not added to the repository, but exists in your local version):
```
jawpintos/sandbox> svn status
M       README.txt
```
  1. Checking differences between your version and version in repository:
```
jawpintos/sandbox> svn diff README.txt
Index: README.txt
===================================================================
--- README.txt	(revision 7)
+++ README.txt	(working copy)
@@ -1 +1 @@
-First version
+Second version
```
  1. Committing (checking in) all your changes in the current directory into the repository with a simple comment that goes with the commit:
```
jawpintos/sandbox> svn ci -m 'my comment'
```
  1. or Committing particular files into the repository:
```
jawpintos/sandbox> svn ci -m 'my comment' README.txt
Sending        README.txt
Transmitting file data .
Committed revision 8.
```
  1. Help on any svn commands:
```
svn help <command>
```