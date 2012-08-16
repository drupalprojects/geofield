<?php

/**
 * @file
 * Database plugin interface
 */

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
