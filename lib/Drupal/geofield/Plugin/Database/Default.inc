<?php

/**
 * @file
 * Definition of DrupalGeofieldPluginDatabaseDefault.
 */

// @todo - Uncomment in D8
//namespace Drupal\geofield\Plugin\Database;

/**
 * Geofield DB plugin default class.
 */
class DrupalGeofieldPluginDatabaseDefault extends DrupalGeofieldPluginDatabaseBase {
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

  public function fieldLoad($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
    /*if ($field['type'] === 'geofield') {
      geophp_load();
      foreach ($items as $delta => $item) {
        $geom = geoPHP::load($item['geom'], 'wkb');
        $item['geom'] = $geom->out('wkt');
      }
    }*/
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
}
