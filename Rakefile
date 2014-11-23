PHP_VERS="5.5.19"
PHP_FILE="php-#{PHP_VERS}.tar.gz"
PHP_SRC="http://de1.php.net/get/#{PHP_FILE}/from/this/mirror"
PHP_MD5="8ef89261aa6bb2d74df8d147f0d183a1"

task :default => [
  :download,
  :clean
]

task :download do
  print_stdout "downloading the PHP #{PHP_VERS} source code..."
  #php_md5_download = %x[wget -4 --no-verbose --show-progress -O - #{PHP_SRC} | tee #{PHP_FILE} | md5]
  php_md5_download = "8ef89261aa6bb2d74df8d147f0d183a1\n"
  php_md5_download = php_md5_download.gsub!("\n", ' ').gsub!(" ", '') 
  if php_md5_download != "#{PHP_MD5}"
    print_stderr "Download failed: md5 of the file downloaded does not match"
  else
    print_stdout "extracting..."
    system "tar -xf #{PHP_FILE}"
  end
end

task :clean do
  if File.exists? "#{PHP_FILE}"
    print_stdout "cleaning..."
    FileUtils.rm_rf "#{PHP_FILE}"
  else
    print_stdout "nothing to do"
  end
end

task :skel do
  print "create skeleton PHP extension file"
end

task :help do
  print "PHP-dzsave extension building tool\n"
  print "  help       print this menu\n"
  print "  download   download the PHP #{PHP_VERS} source code\n"
  print "  clean      remove intermediate files\n"
end

# Auxiliar functions 
private
	def print_stderr(text); print "\e[31m#{text}\e[0m\n"; end
	def print_stdout(text); print "\e[32m#{text}\e[0m\n"; end

