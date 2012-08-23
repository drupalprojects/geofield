<?php

/**
 * @file
 * Definition of DrupalGeofieldPluginDatabaseDiscovery.
 */

// @todo - This will work in D8
//namespace Drupal\geofield\Plugin\Database;

/**
 * Database plugin discovery class.
 */
class DrupalGeofieldPluginDatabaseDiscovery {
  public static function getDefinition($name) {
    $definitions = DrupalGeofieldPluginDatabaseDiscovery::getDefinitions();
    return isset($definitions[$name]) ? $definitions[$name] : array();
  }

  public static function getDefinitions() {
    $hook = 'geofield_db_plugin_info';
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
