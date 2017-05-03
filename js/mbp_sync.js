(function ($, window, document, undefined) {
  Drupal.behaviors.mbp_sync = {
    attach: function (context) {
      $('.mbp-folders li').click(function(e) {
        // A click on the icon just opens the folder structure.
        if (!$(e.target).hasClass('icon')) {
          $('#edit-submit-media-browser-plus').click();
        }
      });
    }
  }
})( jQuery, window, document );