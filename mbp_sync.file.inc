<?php

/**
 * @file
 * File entity specific hooks.
 */

/**
 * Implements hook_file_presave().
 */
function mbp_sync_file_presave($entity) {
  // Check if folder needs to be created.
  if (_mbp_sync_folder_is_skipped($entity)) {
    return;
  }

  // Set appropriate default folder if necessary.
  if (empty($entity->field_folder[LANGUAGE_NONE][0]['tid']) && !isset($entity->migrate)) {
    $root = media_browser_plus_get_media_root_folder();
    $entity->field_folder[LANGUAGE_NONE] = array(array('tid' => $root->tid));
  }

  // Ensure file is stored in the appropriate folder.
  if (!empty($entity->field_folder[LANGUAGE_NONE][0]['tid'])) {
    $folder = taxonomy_term_load($entity->field_folder[LANGUAGE_NONE][0]['tid']);
    $new_path = file_stream_wrapper_uri_normalize(file_uri_scheme($entity->uri) . '://' . media_browser_plus_construct_dir_path($folder) . '/' . drupal_basename($entity->uri));
    // Only move file if necessary.
    if ($entity->uri !== $new_path) {
      mbp_sync_move_file($folder->tid, $entity, NULL, FALSE);
    }
  }
}

/**
 * Validate if folder needs to be created.
 *
 * MBP folder processing is skipped if:
 * - Manually requested by adding the property mbp_bypass to the file entity.
 * - The file has no folder set and has a path in the filesystem defined.
 * - The file is external or missing.
 *
 * @param object $entity
 *   The file entity.
 *
 * @see mbp_sync_file_presave()
 */
function _mbp_sync_folder_is_skipped($entity) {
  $is_skipped = FALSE;
  $conditions = array(
    'bypassed' => !empty($entity->mbp_bypass),
    'no_folder' => (empty($entity->field_folder[LANGUAGE_NONE][0]['tid']) && isset($entity->uri) && file_uri_scheme($entity->uri) . '://' !== $entity->uri),
    'external' => (strpos($entity->uri, 'public://') === FALSE && strpos($entity->uri, 'private://') === FALSE),
    'missing' => !file_exists($entity->uri),
  );

  foreach ($conditions as $condition) {
    if ($condition == TRUE) {
      $is_skipped = TRUE;
    }
  }

  return $is_skipped;
}
