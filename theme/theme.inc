<?php

/**
 * @file
 * theme.inc
 * Contains theme and preprocess functions for Islandora Newspaper Landing Page.
 */

/**
 * Preprocess hook.
 *
 * @param array $variables
 * @global string $base_url
 */
function islandora_newspaper_landing_page_preprocess_islandora_newspaper_landing_page_view(&$variables) {
  global $base_url;

  // Include islandora_newspaper.inc for use of utility functions.
  module_load_include('inc', 'islandora_newspaper', 'includes/utilities');

  // Include custom javascript to handle the read more link.
  drupal_add_js(drupal_get_path('module', 'islandora_newspaper_landing_page') . '/js/read-more.js');

  $islandora_object = $variables['islandora_object'];
  $mods = $islandora_object['MODS']->content;

  if ($mods) {
    $mods_doc = new DOMDocument();
    $mods_doc->loadXML($mods);
    $mods_xpath = new DOMXPath($mods_doc);
    $mods_xpath->registerNamespace('m', 'http://www.loc.gov/mods/v3');

    // Extract MODS data for use.
    $variables['mods']['title'] = $mods_xpath->evaluate('string(//m:mods/m:titleInfo/m:title)');
    $variables['mods']['non_sort'] = $mods_xpath->evaluate('string(//m:mods/m:titleInfo/m:nonSort)');
    $variables['mods']['place'] = $mods_xpath->evaluate('string(//m:mods/m:originInfo/m:place/m:placeTerm)');
    $variables['mods']['geographic'] = $mods_xpath->evaluate('string(//m:mods/m:subject/m:geographic)');
    $variables['mods']['topic'] = $mods_xpath->evaluate('string(//m:mods/m:subject/m:topic)');
    $variables['mods']['temporal'] = $mods_xpath->evaluate('string(//m:mods/m:subject/m:temporal)');
    $variables['mods']['publisher'] = $mods_xpath->evaluate('string(//m:mods/m:originInfo/m:publisher)');
    $variables['mods']['pubDate'] = date('F d, Y', strtotime($mods_xpath->evaluate('string(//m:mods/m:originInfo/m:dateIssued[@point="start"])')));
    $variables['mods']['frequency'] = $mods_xpath->evaluate('string(//m:mods/m:originInfo/m:frequency[@authority="marcfrequency"])');
    $variables['mods']['language'] = $mods_xpath->evaluate('string(//m:mods/m:language[@type="text"])');
    $variables['mods']['note'] = $mods_xpath->evaluate('string(//m:mods/m:note[not(@*)])');
    $variables['mods']['issn'] = $mods_xpath->evaluate('string(//m:mods/m:identifier[@type="issn"])');
    $variables['mods']['credit'] = $mods_xpath->evaluate('string(//m:mods/m:note[@type="credit"])');
    $variables['mods']['prospectus'] = $mods_xpath->evaluate('string(//m:mods/m:note[@type="prospectus"])');

    $pre_titles = $mods_xpath->evaluate('//m:mods/m:relatedItem[@type="preceding"]/m:titleInfo/m:title');
    foreach ($pre_titles as $item) {
      if ($item->nodeValue)
        $variables['mods']['preceding'][] = $item->nodeValue;
    }
    $suc_titles = $mods_xpath->evaluate('//m:mods/m:relatedItem[@type="succeeding"]/m:titleInfo/m:title');
    foreach ($suc_titles as $item) {
      if ($item->nodeValue)
        $variables['mods']['succeeding'][] = $item->nodeValue;
    }
  }

  // Set page title, with non sort if available.
  drupal_set_title($variables['mods']['non_sort'] != "" ? $variables['mods']['non_sort'] . " " . $variables['mods']['title'] : $variables['mods']['title']);

  // If a thumbnail of the object exists, use it, else use default folder image.
  if (isset($islandora_object['TN'])) {
    $variables['front_cover_image'] = $base_url . "/islandora/object/$islandora_object->id/datastream/TN";
  }
  else {
    $variables['front_cover_image'] = $base_url . '/' . drupal_get_path('module', 'islandora_newspaper_landing_page') . '/images/folder.png';
  }

  $issues = array_keys(islandora_newspaper_get_issues($islandora_object));
  if ($issues) {
    $num_issues = count($issues);
    $variables['num_issues'] = $num_issues;
    $variables['first_issue_path'] = $base_url . "/islandora/object/" . $issues[0];
    $variables['last_issue_path'] = $base_url . "/islandora/object/" . $issues[$num_issues - 1];
  }

  $ancestors_field = variable_get('islandora_newspaper_landing_page_ancestors_field', 'ancestors_ms');
  $sort_field = variable_get('islandora_newspaper_landing_page_sort_field', 'PARENT_dateIssued_dt');
  $sort_order = variable_get('islandora_newspaper_landing_page_sort_order', 'asc');

  $variables['front_pages_path'] = $base_url . "/islandora/search/{$ancestors_field}%3A%22{$islandora_object->id}%22%20AND%20RELS_EXT_isPageNumber_literal_ms%3A1?sort={$sort_field}%20{$sort_order}";
  $variables['view_path'] = $base_url . "/islandora/object/" . $islandora_object->id;
  $variables['view_path_label'] = module_exists('islandora_newspaper_calendar_page') ? 'Calendar view' : 'View';
}
