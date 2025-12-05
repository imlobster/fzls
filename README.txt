	[ ! PROTOTYPE STAGE ! ]

fzls ('fuzzy list') is a successor to Unix ls that explicitly
highlights only distinct prefixes of files.

how can it be helpful:

	imagine you have a folder:

# ls
important

	and you make a backup of it:

# cp -r important important-old
# ls
important      important-backup

	you have done some things with the first one, and now you
	want to get rid of the backup .

	you would type this:

# ls
important      important-backup

# rm -rf i

	then you will most likely hit TAB. There are two possible
	consequences:

	first: you will find that you are very careful

# rm -rf i^I
important      important-backup
# rm-rf important-^I
# rm-rf important-backup
#

	second: you will get in trouble

# rm -rf
important      important-backup
# rm-rf important
#

	so how does fzls help in that situation?
	you will just see what you need to type, ALWAYS.

# fzls
|I|mportant      |IMPORTANT-|backup

	you will see that if you type 'i', you might get the wrong
	autocomplete.

	and of course, this is not how it really looks. real fzls
	uses escape codes instead of uppercase or added characters.

so... yes. I will not say you can not live without fzls, but if you
experience the same troubles as I did, feel free to use it.

there are no plans for other sorts, -l or --tree flag, so
combine fzls with the standard ls, or your preferred one, when
needed.
