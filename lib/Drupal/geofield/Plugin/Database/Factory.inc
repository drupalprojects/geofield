<?php

/**
 * @file
 * Definition of Drupal\geofield\Plugin\Database\Factory.
 */

namespace Drupal\geofield\Plugin\Database;

/**
 * Database plugin factory.
 */
class Factory {
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
