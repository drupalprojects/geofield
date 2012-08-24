<?php

/**
 * @file
 * Definition of DrupalGeofieldPluginStorageInterface.
 */

// @todo - Uncomment in D8
//namespace Drupal\geofield\Plugin\Storage;

/**
 * Base interface for connecting to geospatially enabled storage engines.
 */
interface DrupalGeofieldPluginStorageInterface {
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
  public function fieldUpdateField($field, $prior_field, $has_data);
  public function fieldUpdateForbid($field, $prior_field, $has_data);
  public function fieldDeleteField($field);
  public function fieldPurgeField($field);
}
