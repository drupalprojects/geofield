<?php

/**
 * @file
 * Definition of DrupalGeofieldPluginStorageDiscovery.
 */

// @todo - This will work in D8
//namespace Drupal\geofield\Plugin\Storage;

/**
 * Storage plugin discovery class.
 */
class DrupalGeofieldPluginStorageDiscovery {
  public static function getDefinition($name) {
    $definitions = DrupalGeofieldPluginStorageDiscovery::getDefinitions();
    return isset($definitions[$name]) ? $definitions[$name] : array();
  }

  public static function getDefinitions() {
    $hook = 'geofield_plugin_storage_info';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      foreach ($function() as $type => $definition) {
        $definition['module'] = $module;
        if (!isset($definition['extension'])) {
          $definition['extension'] = 'inc';
        }
        $definitions[$type] = $definition;
      }
    }
    drupal_alter($hook, $definitions);
    return $definitions;
  }
}
