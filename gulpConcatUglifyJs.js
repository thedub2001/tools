// from http://stackoverflow.com/questions/28189177/best-way-to-concat-and-uglify-js-in-gulp
// https://github.com/gulpjs/gulp

gulp.task('javascript:vendor', function(callback) {
  return gulp.src([
      './node_modules/jquery/dist/jquery.js',
      './node_modules/underscore/underscore.js',
      './node_modules/backbone/backbone.js'
    ])
    .pipe(sourcemaps.init())
    // getBundleName creates a cache busting name
    .pipe(concat(getBundleName('vendor')))
    .pipe(uglify())
    .pipe(sourcemaps.write('./'))
    .pipe(gulp.dest('./public/app'))
    .on('error', handleErrors);
});
