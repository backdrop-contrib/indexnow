<?php
/**
 * @file indexnow.admin.inc
 * Admin form to manage module settings
 *
 */

/**
 * Define the form for module settings
 *
 */
function indexnow_settings_form($form, &$form_state) {
  $config  = config('indexnow.settings');
  $api_key = $config->get('indexnow_api_key');
 
  $form['indexnow_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('IndexNow API key'),
    '#default_value' => $api_key,
    '#size' => 96,
    '#description' => t("Generate a <a href='@key'>free API key</a>, copy and paste the generated API key to the field above.", array('@key' => 'https://www.bing.com/indexnow#generateApiKey')) . '<br>'
     . t('Alternatively, you can create any set of 8 - 128 characters containing only Latin letters and numbers, for example: ') . '<br>' 
    . '<em>UvD8ykmdNLlxYEi2LkhJjYOH2kyQbJqM3cAKT4fs</em>' . '<br>'
    . t('Do not worry about creating a verification file, it will be created for you automatically.'), 
  );
  
  $form['searchengine'] = array(
    '#type' => 'select',
    '#title' => t('Search engine'),
    '#options' => array(
      'bing' => t('Bing'),
      'yandex' => t('Yandex'),
    ),
    '#default_value' => $config->get('searchengine'),
    '#description' => t('Select preferred search engine.') . '<br>'
    . t('Please note: starting November 2021, IndexNow-enabled search engines will share immediately all URLs submitted to all other IndexNow-enabled search engines, so when you notify one, you will notify all search engines.'),
  );
  
  $node_types    = node_type_get_types();
  $content_types = array();
  
  foreach ($node_types as $key => $value) {
    $content_types[$key] = $value->name;
  }
  
  $form['content_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#options' => $content_types,
    '#default_value' => $config->get('content_types'),
    '#description' => t('Select what content types to submit when you create or update nodes.'),
  );
  
  $form['actions'] = array(
    '#type' => 'actions',
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}
  
/**
 * Implements form custom validate.
 */
function indexnow_settings_form_validate($form, &$form_state) {
  $indexnow_api_key = trim($form_state['values']['indexnow_api_key']);
  $content_types = current($form_state['values']['content_types']);

  if (empty($indexnow_api_key) || strlen($indexnow_api_key) < 8) {
    form_set_error('indexnow_api_key', t('The "IndexNow API key" field value cannot be shorter than 8 characters.'));
  }
  
  if (empty($content_types)) {
    form_set_error('content_types', t('At least one content type must be selected.'));
  }
}

/**
 * Implements hook_submit().
 */
function indexnow_settings_form_submit($form, &$form_state) {
  global $user;
  $config  = config('indexnow.settings');
  $api_key = trim($form_state['values']['indexnow_api_key']);
  
  $config->set('indexnow_api_key', $api_key);
  $config->set('searchengine',     $form_state['values']['searchengine']);
  $config->set('content_types',    $form_state['values']['content_types']);
  $config->save();
  
  indexnow_file_save($api_key);
  backdrop_flush_all_caches();
  
  watchdog('IndexNow', t('Settings changed by @user.', array('@user' => $user->name)));
  backdrop_set_message(t('Settings have been saved.'));
}