<?php

/**
 * @file
 * Definition of Drupal\geofield\Plugin\Database\Base.
 */

namespace Drupal\geofield\Plugin\Database;

/**
 * Geofield DB plugin base class.
 */
class Base implements DatabaseInterface {
  public function getFieldSchema() {
    return array();
  }

  public function fieldSettingsForm($field, $instance, $has_data) {
    return array();
  }

  public function fieldLoad($entity_type, $entities, $field, $instances, $langcode, &$items, $age) {
  }

  public function fieldValidate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  }

  public function fieldIsEmpty($item, $field) {
    return FALSE;
  }

  public function fieldPresave($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldInsert($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldUpdate($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldDelete($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldDeleteRevision($entity_type, $entity, $field, $instance, $langcode, &$items) {
  }

  public function fieldUpdateField($field, $prior_field, $has_data) {
  }

  public function fieldUpdateForbid($field, $prior_field, $has_data) {
  }

  public function fieldDeleteField($field) {
  }
}
