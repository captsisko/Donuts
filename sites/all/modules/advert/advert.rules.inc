<?php

function advert_rules_action_info(){
	/*$actions['advert_publish_product_display_node'] = array(
		'label' => t('Publish Product Display Node'), 
		'group' => t('Advert Functions'), 
		'parameter' => array(
			'product' => array(
				'type' => array('uri'),
				'label' => t('Product Display Path'),
        		// 'wrap' => true,
        		// 'save' => true,
          		// 'restriction' => 'input',
			),
		'callbacks' => array(
	        'access' => 'rules_action_entity_createfetch_access2',
	        'form_alter' => 'rules_action_type_form_alter',
	      ),
		),
	);*/

	$actions['advert_publish_product_display_node'] = array(
      'label' => t('Fetch product-display id'),
      'parameter' => array(
        'type' => array(
          'type' => 'uri',
          'label' => t('Advert Functions'),
          'options list' => 'rules_entity_action_type_options2',
          'description' => t('Specifies the product-display url.'),
          // 'restriction' => 'input',
        ),
        // 'id' => array('type' => 'unknown', 'label' => t('Identifier')),
      ),
      'provides' => array(
        'entity_fetched' => array('type' => 'integer', 'label' => t('Fetched entity')),
      ),
      'group' => t('Entities'),
      'access callback' => 'rules_entity_action_access',
      // 'base' => 'rules_action_entity_fetch',
      /*'callbacks' => array(
        'access' => 'rules_action_entity_createfetch_access2',
        'form_alter' => 'rules_action_type_form_alter',
      ),*/
    );
	
	return $actions;
}

function advert_publish_product_display_node($path = null){
	$parts = explode('node/', $path);
	// $node = node_load( (int) $parts[1]);
	// $node->status = 1;
	// node_save($node);
	return 7;//$parts[1];
}

function rules_entity_action_type_options2($element, $name = NULL) {
  // We allow calling this function with just the element name too. That way
  // we ease manual re-use.
  $name = is_object($element) ? $element->getElementName() : $element;
  return ($name == 'entity_create') ? rules_entity_type_options2('create') : rules_entity_type_options2();
}

function rules_entity_type_options2($key = NULL) {
  $info = entity_get_info();
  $types = array();
  foreach ($info as $type => $entity_info) {
    if (empty($entity_info['configuration']) && empty($entity_info['exportable'])) {
      if (!isset($key) || entity_type_supports($type, $key)) {
        $types[$type] = $entity_info['label'];
      }
    }
  }
  return $types;
}

function rules_action_entity_createfetch_access2(RulesAbstractPlugin $element) {
  $op = $element->getElementName() == 'entity_create' ? 'create' : 'view';
  return entity_access($op, $element->settings['type']);
}