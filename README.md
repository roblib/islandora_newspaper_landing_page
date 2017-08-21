# Islandora Newspapers Landing Page

## Introduction

This module provides a landing page for Islandora Newspaper objects. 
It appears as an "About" tab when viewing a Newspaper. It appears first
in order (on the left) but does not become the default tab.

![Screenshot](https://user-images.githubusercontent.com/1943338/29537535-7ec2a606-8698-11e7-9b4f-e733e31de618.png)

## Requirements

This module requires the following modules:

* [Islandora Newspaper Solution Pack](https://github.com/Islandora/islandora_solution_pack_newspaper)

Additionally, the 'All first pages' link requires that you have indexed 
the title of the parent newspaper (e.g. a field contains "The Chronicle")on the 
individual _newspaper page_ objects.
 
An alternate branch, 7.x.1.3-ancestors, relies on indexing the pids of ancestors, rather than the 
parent's title, and will provide a more reliable method of finding 'All first pages.'