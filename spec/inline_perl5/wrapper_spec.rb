describe InlinePerl5::Wrapper do
  it "do some basic perl maths" do
    wrapper = InlinePerl5::Wrapper.new('1++')
    wrapper.run.should == 2
  end
end