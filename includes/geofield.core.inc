<?php

/**
 * @file
 * Database plugin intefaces and classes
 */

/**
 * Database plugin discovery class.
 */
class GeofieldDatabasePluginDiscovery {
  public static function getDefinition($name) {
    $definitions = GeofieldDatabasePluginDiscovery::getDefinitions();
    return isset($definitions[$name]) ? $definitions[$name] : array();
  }

  public static function getDefinitions() {
    $hook = 'geofield_db_plugin_info';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      foreach ($function() as $type => $definition) {
        $definition['module'] = $module;
        $definitions[$type] = $definition;
      }
    }
    drupal_alter($hook, $definitions);
    return $definitions;
  }
}

/**
 * Database plugin factory.
 */
class GeofieldDatabasePluginFactory {
  public static function getInstance($name) {
    if (empty($name)) {
      return NULL;
    }
    $definition = GeofieldDatabasePluginDiscovery::getDefinition($name);
    if (empty($definition) || !class_exists($definition['class'])) {
      return NULL;
    }
    $class = $definition['class'];
    return new $class();
  }
}

/**
 * Base interface for connecting to geospatially enabled databases.
 */
interface GeofieldDatabaseInterface {
  public function getFieldSchema();
  public function fieldSettingsForm($field, $instance, $has_data);
  public function fieldLoad($entity_type, $entities, $field, $instances, $langcode, &$items, $age);
  public function fieldValidate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors);
  public function fieldIsEmpty($item, $field);
  public function fieldPresave($entity_type, $entity, $field, $instance, $langcode, &$items);
  public function fieldInsert($entity_type, $entity, $field, $instance, $langcode, &$items);
  public function fieldUpdate($entity_type, $entity, $field, $instance, $langcode, &$items);
  public function fieldDelete($entity_type, $entity, $field, $instance, $langcode, &$items);
  public function fieldDeleteRevision($entity_type, $entity, $field, $instance, $langcode, &$items);
  public function fieldPrepareTranslation($entity_type, $entity, $field, $instance, $langcode, &$items, $source_entity, $source_langcode);
  public function fieldUpdateField($field, $prior_field, $has_data);
  public function fieldUpdateForbid($field, $prior_field, $has_data);
  public function fieldDeleteField($field);
}

/**
 * Our default class.
 */
class GeofieldDatabaseDefault implements GeofieldDatabaseInterface {
  public function getFieldSchema() {
    return array(
      'columns' => array(
        'geom' => array(
          'type' => 'blob',
          'size' => 'big',
          'not null' => FALSE,
        ),
        'geo_type' => array(
          'type' => 'text',
          'size' => 'normal',
          'not null' => FALSE,
        ),
        'lat' => array(
          'type' => 'numeric',
          'precision' => 18,
          'scale' => 12,
          'not null' => FALSE,
        ),
        'lon' => array(
          'type' => 'numeric',
          'precision' => 18,
          'scale' => 12,
          'not null' => FALSE,
        ),
        'left' => array(
          'type' => 'numeric',
          'precision' => 18,
          'scale' => 12,
          'not null' => FALSE,
        ),
        'top' => array(
          'type' => 'numeric',
          'precision' => 18,
          'scale' => 12,
          'not null' => FALSE,
        ),
        'right' => array(
          'type' => 'numeric',
          'precision' => 18,
          'scale' => 12,
          'not null' => FALSE,
        ),
        'bottom' => array(
          'type' => 'numeric',
          'precision' => 18,
          'scale' => 12,
          'not null' => FALSE,
        ),
        'srid' => array(
          'type' => 'int',
          'unsigned' => TRUE,
          'not null' => FALSE,
          'default' => 4326,
        ),
        'accuracy' => array(
          'type' => 'int',
          'not null' => FALSE,
        ),
        'source' => array(
          'type' => 'text',
          'not null' => FALSE,
        ),
      ),
    );
  }

  public function fieldSettingsForm($field, $instance, $has_data) {
    return array();
  }

  public function fieldLoad($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
    /*if ($field['type'] === 'geofield') {
      geophp_load();
      foreach ($items as $delta => $item) {
        $geom = geoPHP::load($item['geom'], 'wkb');
        $item['geom'] = $geom->out('wkt');
      }
    }*/
  }

  public function fieldValidate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  }

  public function fieldIsEmpty($item, $field) {
    if (isset($item['input_format'])) {
      switch ($item['input_format']) {
        case GEOFIELD_INPUT_LAT_LON:
          return ((trim($item['geom']['lat']) == '') || (trim($item['geom']['lon']) == ''));
        case GEOFIELD_INPUT_BOUNDS:
          return ((trim($item['geom']['top']) == '') || (trim($item['geom']['right']) == '') ||
          (trim($item['geom']['bottom']) == '') || (trim($item['geom']['left']) == ''));
      }
    }
    //@@TODO: Check if it's an empty geometry as per geoPHP $geometry->empty()
    return empty($item['geom']);
  }

  public function fieldPresave($entity_type, $entity, $field, $instance, $langcode, &$items) {
    foreach ($items as $delta => $item) {
      $items[$delta] = geofield_compute_values($item);
    }
  }

  public function fieldInsert($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldUpdate($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldDelete($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldDeleteRevision($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldPrepareTranslation($entity_type, $entity, $field, $instance, $langcode, &$items, $source_entity, $source_langcode) {
  }

  public function fieldUpdateField($field, $prior_field, $has_data) {
  }

  public function fieldUpdateForbid($field, $prior_field, $has_data) {
  }

  public function fieldDeleteField($field) {
  }
}
