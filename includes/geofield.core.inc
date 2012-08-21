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
    $definitions = GeofieldDatabasePluginFactory::getDefinitions();
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
}
