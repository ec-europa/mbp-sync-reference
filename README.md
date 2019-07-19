# MBP sync

This module allows using [Media Browser Plus](https://www.drupal.org/project/media_browser_plus)
(MBP) Drupal contrib module on NextEuropa platform subsites.

## Description

### When?

You want to use this module when implementing Media Browser Plus and achieve these two actions:

- Automatically build the folder tree structure in "media folder" taxonomy vocabulary.
- Fix hardcoded links to files referenced in your contents.

### Why?

If your website already has a folder tree structure under sites/default/files, it can be tedious
to manually make the "media folder" taxonomy vocabulary to mirror this tree. Using mbp_sync will
programmatically build it for you in one command.

If your contents contain hardcoded links to files, moving a file from a folder to another
will break the links.

For instance, if your content reference a pdf file as is:

```
<a href="https://your-project.eu/sites/yourproject/files/pdffile.pdf">Pdf file</a>
```

Moving this file through MBP back-office interface from a folder to another one
will break the link.

### How?
mbp_sync provides two Drush commands:

- mbpt: Parses the file entities and assign the term folders to media folder vocabulary.
- mpbf: Parses entities for hard-coded links and replaces them with file URL tokens or media tags for images.

## Installation

In your site.make add the following lines:

```
projects[mbp_sync][download][type] = git
projects[mbp_sync][download][url] = https://github.com/ec-europa/mbp-sync-reference.git
projects[mbp_sync][download][tag] = @releaseNumber
projects[mbp_sync][subdir] = custom
```

## Authors

Andras Szilagyi (drishu) and Victor Bourgade (Aporie)
