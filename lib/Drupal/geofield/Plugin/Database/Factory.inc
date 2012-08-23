<?php

/**
 * @file
 * Definition of DrupalGeofieldPluginDatabaseFactory.
 */

// @todo - Uncomment in D8
//namespace Drupal\geofield\Plugin\Database;

/**
 * Database plugin factory.
 */
class DrupalGeofieldPluginDatabaseFactory {
  public static function getInstance($name) {
    if (empty($name)) {
      return NULL;
    }
    $definition = Drupal\geofield\Plugin\Database\Discovery::getDefinition($name);
    module_load_include($definition['extension'], $definition['module'], $definition['file']);
    if (empty($definition) || !class_exists($definition['class'])) {
      return NULL;
    }
    $class = $definition['class'];
    return new $class();
  }
}
