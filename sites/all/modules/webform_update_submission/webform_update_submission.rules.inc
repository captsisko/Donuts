<?php

function webform_update_submission_rules_action_info() {
  // $actions = array();
  $actions['webform_update_submission_action_commerce_api_create_order'] = array(
    'label' =>  'Execute code to create commerce order',
    'group' => t('Webform Payment'),
    'parameter' =>  array(
      'node' =>  array(
        'type'  =>  'node',
        'label' =>  'specify webform-commerce node',
        'save'  =>  false,
      ),
      'productID' =>  array(
        'type'  =>  'integer',
        'label' =>  'specify product ID',
        'save'  =>  false,
      ),
      'submissionID' =>  array(
        'type'  =>  '*',
        'label' =>  'specify webform submission ID',
        'save'  =>  false,
      ),
    ),
    // 'named parameter' => TRUE,
  );

  return $actions;
}

/*function webform_update_submission_action_get_webform_submission_id($webform=null){
  drupal_set_message("Testing function for retrieving SID");
  dsm($webform, 'checking a webform for the SID');
}*/

function webform_update_submission_action_commerce_api_create_order($node=null, $pid=null, $sid=null){
  dsm($node, 'webform-commerce node');
  dsm($sid);
  drupal_set_message("Testing: PID#{$pid}, SID#{$sid['sid']}");

  /*module_load_include('inc', 'webform', 'includes/webform.submissions');
  $submission = webform_get_submission(9, $sid['sid']);
  dsm($submission, 'submission');
  $submission->data[3]['value'][0] = 'yes';
  dsm($submission, 'submission post updating');
  $node = node_load(9);
  webform_submission_update($node, $submission);*/

  global $user;
  $product_id = $pid;
  // Create the new order in checkout; you might also check first to
  // see if your user already has an order to use instead of a new one.
  $order = commerce_order_new($user->uid, 'checkout_checkout');

  // Save the order to get its ID.
  commerce_order_save($order);

  // Load whatever product represents the item the customer will be
  // paying for and create a line item for it.
  $product = commerce_product_load($product_id);
  $line_item = commerce_product_line_item_new($product, 1, $order->order_id);

  // Save the line item to get its ID.
  commerce_line_item_save($line_item);

  // Add the line item to the order using fago's rockin' wrapper.
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $order_wrapper->commerce_line_items[] = $line_item;

  // Save the order again to update its line item reference field.
  commerce_order_save($order);

  /*******************************************/
    module_load_include('inc', 'webform', 'includes/webform.submissions');
    $submission = webform_get_submission($node->nid, $sid['sid']);
    // dsm($submission, 'submission');
    $submission->data[3]['value'][0] = 'yes';
    // dsm($submission, 'submission post updating');
    // $node = node_load(9);
    webform_submission_update($node, $submission);
  /*******************************************/

  // Redirect to the order's checkout form. Obviously, if this were a
  // form submit handler, you'd just set $form_state['redirect'].
  drupal_goto('checkout/' . $order->order_id);
}