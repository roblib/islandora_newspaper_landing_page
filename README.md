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
the PIDs of an object's ancestors. This can be done by following the [instructions here](https://gist.github.com/daniel-dgi/6001819)

## Configuration

Configure which solr fields are used when displaying "All Front Pages" at admin/islandora/tools/newspaper_landing_page.

