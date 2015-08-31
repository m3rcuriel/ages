#Working on Ages
Ages is a world-generation and exploration software based on procedural generation and complex modelling. We're probably dumber then we think we are.

##Making Changes
+ Create a topic branch off of where you want to base your work.
	+ This is usually `master`
	+ Name your branch something relevant to the change
	+ To create a topic branch, use `git checkout master` followed by `git checkout -b <name>`. Avoid working directly on `master`.
+ Make your best efforts to follow [LLVM Code Standards](http://llvm.org/docs/CodingStandards.html)
+ Large changes should be fully documented in code
	+ possible doc generation to come
	
##Committing your changes
+ Check for whitespace errors with `git diff --check`
+ Describe your changes in the commit description
	+ Message should use the imperative
		+ _If applied, this commit will_ ...
	+ Limit message to 50 characters
+ Describe changes in more detail on a new line

Example commit message:
> Patch memory deletion bug


