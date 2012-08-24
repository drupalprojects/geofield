<?php

/**
 * @file
 * Definition of DrupalGeofieldPluginStorageFactory.
 */

// @todo - Uncomment in D8
//namespace Drupal\geofield\Plugin\Storage;

/**
 * Storage plugin factory.
 */
class DrupalGeofieldPluginStorageFactory {
  public static function getInstance($name) {
    if (empty($name)) {
      return NULL;
    }
    $definition = DrupalGeofieldPluginStorageDiscovery::getDefinition($name);
    module_load_include($definition['extension'], $definition['module'], $definition['file']);
    if (empty($definition) || !class_exists($definition['class'])) {
      return NULL;
    }
    $class = $definition['class'];
    return new $class();
  }
}
