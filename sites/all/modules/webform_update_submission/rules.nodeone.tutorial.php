<?php

function webform_update_submission_rules_event_info() {
  $events = array();
  $events['webform_payment'] = array(
      'label' => t('Webform Payment'),
      'group' => t('Webform Payment'),
      'variables' => array(
        'current_user' => array('type' => 'user', 'label' => t('The current logged in user.')),
        'webform' => array('type' => 'node', 'label' => t('The webform/Commerce node.')),
        'some_text' => array('type' => 'text', 'label' => t('Some arbitray text.')),
    ),
  );
  if(module_exists('views')){
    $events['webform_update_submission_event_view_render'] =array(
        'label' => 'A view is going to be rendered',
        'group' => t('Webform Payment'),
        'variables' => array(
          'view_name' => array(
            'type' => 'text',
            'label' => 'view name',
          ),
        ),
    );
  }
  return $events;
}

function webform_update_submission_event_view_render($view_name=null){
  drupal_set_message("testing ... testing: {$view_name}");
}

/**********************************************************/
function webform_update_submission_rules_action_info() {
  $actions = array(
    'webform_update_submission_action_hello_world' => array(
      'label' =>  'print hello world',
      'group' => t('Webform Payment'),
    ),

    'webform_update_submission_action_hello_user' => array(
      'label' =>  'Say hello to the selected user',
      'group' => t('Webform Payment'),
      'parameter' =>  array(
        'account' =>  array(
          'type'  =>  'user',
          'label' =>  'user to say hello to',
          'save'  =>  false,
        ),
      )
    ),
  );

    if(module_exists('views')){
      $actions['webform_update_submission_action_get_view_results'] = array(
        'label' => 'Get number of results in a view',
        'group' => t('Webform Payment'),
        'parameter' => array(
          'view_name' => array(
          'type' => 'text',
          'label' => 'View to load the number of results',
          'options list' => 'webform_update_submission_view_list',
          'description' => 'select the view you wish to use',
          // 'restriction' => 'input',
          ),
        ),
        'provides' => array(
          'number_of_results' => array(
            'type' => 'integer',
            'label' => 'number of views result',
          ),
        ),
      );
    }

  return $actions;
}

function webform_update_submission_view_list(){
  $views = views_get_all_views();
  dsm($views, 'called from webform_update_submission_view_list');

  foreach($views as $view_name=>$view_object){
    $views[$view_name] = (isset($view_object->human_name)) ? $view_object->human_name : $view_name;
  }
  return $views;
}
function webform_update_submission_action_get_view_results($view_name=null){
  $results = views_get_view_result($view_name);
  return array(
    'number_of_results' => count($results)
  );
}

function webform_update_submission_action_hello_world(){
  drupal_set_message("RULE: Hello World!");
}

function webform_update_submission_action_hello_user($account){
  drupal_set_message(t('Hello @username!', array('@username'=>$account->name)));
  // dsm($account);
}

/*********************************************************/
function webform_update_submission_rules_condition_info() {
  if( !module_exists('views') )
    return;
  $conditions = array(
    'webform_update_submission_rules_conditions_view_base_table' => array(
      'label' => t('View has base table'),
       'group' => t('Webform Payment'),
       'parameter' => array(
          'view_name' => array(
            'type' => 'text',
            'label' => t('View to check'),
            'options list' => 'webform_update_submission_view_list',
          ),
          'base_table' => array(
              'type' => 'text',
              'label' => t('The machine name of the base table'),
              // 'restriction' => 'input',
          ),
        ),
    ),
  );
  return $conditions;
}

function webform_update_submission_rules_conditions_view_base_table($view_name=null, $base_table=null){
    $view = views_get_view($view_name);
    return $view->base_table == $base_table;
}