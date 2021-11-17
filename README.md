IndexNow
========

This module provides an easy way for websites owners to instantly inform 
search engines about latest content changes on their website.

More information about IndexNow protocol you can get on [official site.](https://www.indexnow.org)

Installation
------------
Install this module using the official Backdrop CMS instructions at https://backdropcms.org/guide/modules    
**Please note:** [PHP cURL](http://php.net/manual/en/curl.setup.php) library must be installed on your server. 

Configuration and usage
-----------------------
Administration page is available via menu *Administration > Configuration > 
Metadata > IndexNow* (admin/config/metadata/indexnow). 

- first you need generate or use your own IndexNow API key as described below "IndexNow API key" field;   
- select your prefered search engine;
- select what content types to submit when you create or update nodes.

When you save the settings, a text key file to verify the ownership of the site 
will be generated for you automatically.

Now, every time cron runs, the latest content changes will be automatically sent 
to all participating search engines.    
Thus, multiple edits of the same node do not result in multiple submissions.

Known issues
------------
If you've enabled "fast_404()" in your "settings.php" file, search engines most likely 
won't be able to retrieve your text key file to verify site ownership.    
To avoid this problem, consider removing the "txt" extension from "404_fast_paths".

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

IndexNow is offered under the terms of the Attribution-ShareAlike Creative 
Commons License and has support from Microsoft Bing, Yandex.

Current Maintainer
------------------
Vladimir (https://github.com/findlabnet/)

More information
----------------
For bug reports, feature or support requests, please use the module 
issue queue at https://github.com/backdrop-contrib/indexnow/issues.
