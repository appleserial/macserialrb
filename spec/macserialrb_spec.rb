RSpec.describe Macserialrb do
  it "has a version number" do
    expect(Macserialrb::VERSION).not_to be nil
  end

  it "#models, return a model array" do
    expect(Macserialrb.models).to be_an_instance_of(Array)
  end

  it "#generate,  pass the model option will give me the productName/SystemSerialNumber/MLB" do
    model = Macserialrb.models.sample

    info = Macserialrb.generate model: model

    expect(info[:productName]).to eq model
    expect(info[:SystemSerialNumber]).not_to be nil
    expect(info[:MLB]).not_to be nil
  end
end
